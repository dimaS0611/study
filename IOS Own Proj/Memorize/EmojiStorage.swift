//
//  EmojiStorage.swift
//  Memorize
//
//  Created by Dima Semenovich on 11/26/20.
//  Copyright © 2020 Dima Semenovich. All rights reserved.
//

import Foundation

class EmojiStorage
{
    enum emojis{
        case helloween
        case christmas
        case flags
        case people
        case smiles
    }
    
    var EmojisArray : [emojis:Array<String>] = [emojis.helloween : ["👻", "🎃", "🧟‍♂️", "🧙‍♀️", "🧛🏻‍♂️", "🕷", "🦇", "💀", "⚰️"],
                        emojis.christmas : [""],
                        emojis.flags : [""],
                        emojis.people : [""],
                        emojis.smiles : [""]]
    
    func getArrayOfTheme(key: emojis) -> Array<String>
    {
        return EmojisArray[key] ?? ["👻", "🎃", "🧟‍♂️", "🧙‍♀️", "🧛🏻‍♂️", "🕷", "🦇", "💀", "⚰️"]
    }
}
