//
//  ContentView.swift
//  client
//
//  Created by Otmane on 5/26/23.
//

import SwiftUI


final class ViewModel: ObservableObject {
    private(set) var result: String = ""
    
    private var client = Client(host: "0.0.0.0", port: 5500);
    
    init() {
        client.start()
        
        
        client.send(data: "HELLO".data(using: .utf8)!)
        sleep(1)
        client.receive() { (result) in
            print("string: \(result)")
        }
        
    }
    
    func runProtocol(firstNumber: String, secondNumber: String, operation: String) {
        if firstNumber.isEmpty {
            self.updateResult(string: "First number cant be empty")
            return
        }
        
        if secondNumber.isEmpty {
            self.updateResult(string: "Second number cant be empty")
            return
        }
        
        if operation == "--" {
            self.updateResult(string: "Choose an operation to continue")
            return
        }
        
        self.updateResult(string: "Loading ...")
        
        let operationString = operation + " " + String(String(firstNumber.reversed()).padding(toLength: 128, withPad: "0", startingAt: 0).reversed()) + " " + String(String(secondNumber.reversed()).padding(toLength: 128, withPad: "0", startingAt: 0).reversed())
        
        
        print("operationString \(operationString)")
        
        client.send(data: "CALC".data(using: .utf8)!)
        sleep(1)
        client.send(data: operationString.data(using: .utf8)!)
        
        client.receive() { (socketRes) in
            print("string: \(socketRes)")
            
            let res = socketRes.split(separator: " ")
            if let last = res.last, res.first == "ERR" {
                self.updateResult(string: "Error, " + last)
                return
            }
            
            print("res.last: \(Double(res.last ?? "") ?? 0)")
            self.updateResult(string: "Result: \(Double(res.last ?? "") ?? 0)")
        }
    }
    
    private func updateResult(string: String) {
        self.result = string
        self.objectWillChange.send()
    }
    
    func end(){
        client.send(data: "ENDP".data(using: .utf8)!)
    }
}

struct ContentView: View {
    @State private var firstNumber: String = ""
    @State private var secondNumber: String = ""
    
    @State private var operation = "--"
    let operations = ["--", "ADD", "SUB", "DIV", "MLP"]
    
    
    @StateObject var viewModel = ViewModel()
    
    
    var body: some View {
        VStack(alignment: .leading) {
            HStack(alignment: .center) {
                Image(systemName: "number")
                    .frame(width: 32.0, height: 32.0)
                    .imageScale(.large)
                    .foregroundColor(.accentColor)
                
                Text("Protocol Calculator!")
                    .font(.title)
                    .fontWeight(.semibold)
                    .multilineTextAlignment(.center)
            }
            .padding(.all)
            
            HStack(alignment: .center) {
                TextField(
                    "First number",
                    text: $firstNumber
                )
                
                Picker("", selection: $operation) {
                    ForEach(operations, id: \.self) {
                        Text($0)
                    }
                }
                
                
                TextField(
                    "Second number",
                    text: $secondNumber
                )
            }
            .padding(.all)
            
            HStack() {
                Button("Show result") {
                    viewModel.runProtocol(firstNumber: firstNumber, secondNumber: secondNumber, operation: operation)
                }
                
                Text(viewModel.result)
                    .font(.headline)
                    .fontWeight(.semibold)
                    .multilineTextAlignment(.leading)
            }
            .padding(.all)
            
        }
        .padding(.all)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
