//
//  connection.swift
//  client
//
//  Created by Otmane on 5/26/23.
//

import Foundation
import Network

@available(macOS 10.14, *)
class ClientConnection {
    
    let  nwConnection: NWConnection
    let queue = DispatchQueue(label: "Client connection Q")
    
    init(nwConnection: NWConnection) {
        self.nwConnection = nwConnection
    }
    
    var didStopCallback: ((Error?) -> Void)? = nil
    
    func start() {
        print("connection will start")
        nwConnection.stateUpdateHandler = stateDidChange(to:)
        nwConnection.start(queue: queue)
    }
    
    private func stateDidChange(to state: NWConnection.State) {
        switch state {
        case .waiting(let error):
            connectionDidFail(error: error)
        case .ready:
            print("Client connection ready")
        case .failed(let error):
            connectionDidFail(error: error)
        default:
            break
        }
    }
    
    func receive(completion: @escaping (_ string: String) -> Void) -> Void	 {
        nwConnection.receive(minimumIncompleteLength: 1, maximumLength: 65536) { (data, _, isComplete, error) in
            if let data = data, !data.isEmpty {
                let  message = String(data: data, encoding: .utf8) ?? ""
                print("connection did receive, data: \(data as NSData) string: \(message)")
                
                completion(message);
            }
            if let error = error {
                self.connectionDidFail(error: error)
            }
        }
    }
    
    func send(data: Data) {
        nwConnection.send(content: data, isComplete: true, completion: .contentProcessed( { error in
            if let error = error {
                self.connectionDidFail(error: error)
                return
            }
            print("connection did send, data: \(data as NSData)")
        }))
    }
    
    func stop() {
        print("connection will stop")
        stop(error: nil)
    }
    
    private func connectionDidFail(error: Error) {
        print("connection did fail, error: \(error)")
        self.stop(error: error)
    }
    
    private func connectionDidEnd() {
        print("connection did end")
        self.stop(error: nil)
    }
    
    private func stop(error: Error?) {
        self.nwConnection.stateUpdateHandler = nil
        self.nwConnection.cancel()
        if let didStopCallback = self.didStopCallback {
            self.didStopCallback = nil
            didStopCallback(error)
        }
    }
}
