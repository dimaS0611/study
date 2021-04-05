//
//  EmojiGameMenu.swift
//  Memorize
//
//  Created by Dima Semenovich on 11/15/20.
//  Copyright © 2020 Dima Semenovich. All rights reserved.
//

import SwiftUI

struct EmojiGameMenu: View {
    var store: [String: [String]] = ["Halloween" : ["👻", "🎃", "🧟‍♂️", "🧙‍♀️", "🧛🏻‍♂️", "🕷", "🦇", "💀", "⚰️"]]
    
    var body: some View {
        
        let keys = store.map{$0.key}
        let values = store.map{$0.value}
        
        return List{
            ForEach(keys.indices){ index in
                Text(keys[index])
            }
        }
    }
}


struct EmojiGameMenu_Previews: PreviewProvider {
    static var previews: some View {
        EmojiGameMenu()
    }
}
/*
struct EmojisTheme
{
    var id : String { self.id }
    var name : String
    var EmojiArray: Array<String>
    
    init(name: String, EmojiArray: Array<String>)
    {
        self.name = name
        self.EmojiArray = EmojiArray
    }
}

var store: [String: [String]] = ["Halloween" : ["👻", "🎃", "🧟‍♂️", "🧙‍♀️", "🧛🏻‍♂️", "🕷", "🦇", "💀", "⚰️"]]
*/
