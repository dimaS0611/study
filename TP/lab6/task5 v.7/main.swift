//
//  main.swift
//  Taks 5
//
//  Created by Dmitry Semenovich on 2.04.21.
//

import Foundation

print("Enter the line to swap first and last words")

let input = readLine()

var wordsArr = input?.split(separator: " ").map(String.init)

wordsArr!.swapAt(0, wordsArr!.count-1)

for word in wordsArr!
{
    print(word, " ", terminator: "")
}
