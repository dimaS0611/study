//
//  Array+Only.swift
//  Memorize
//
//  Created by Dima Semenovich on 7/29/20.
//  Copyright © 2020 Dima Semenovich. All rights reserved.
//

import Foundation

extension Array {
    var only: Element? {
        count == 1 ? first : nil
    }
}
