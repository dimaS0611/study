//
//  Array+identifiable.swift
//  Memorize
//
//  Created by Dima Semenovich on 7/29/20.
//  Copyright © 2020 Dima Semenovich. All rights reserved.
//

import Foundation

extension Array where Element: Identifiable {
    func firstIndex(matching: Element) -> Int? {
    for index in 0..<self.count {
        if self[index].id == matching.id {
            return index
        }
    }
    return nil
}}
