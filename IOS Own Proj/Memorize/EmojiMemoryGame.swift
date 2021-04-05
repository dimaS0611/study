//
//  EmojiMemoryGame.swift
//  Memorize
//
//  Created by Dima Semenovich on 7/23/20.
//  Copyright © 2020 Dima Semenovich. All rights reserved.
//

import SwiftUI

class EmojiMemoryGame: ObservableObject {
    
    var emojisContent: Array<String>

    @Published private var model: MemoryGame<String>
    
    init(emojisArray: Array<String>) {
        self.emojisContent = emojisArray
         model = EmojiMemoryGame.createMemoryGame(emojis: emojisContent)
    }
    
    static func createMemoryGame(emojis: Array<String>?) -> MemoryGame<String> {
        let defaultEmojis: Array<String> = ["👻", "🎃", "🧟‍♂️", "🧙‍♀️", "🧛🏻‍♂️", "🕷", "🦇", "💀", "⚰️"]
        return MemoryGame<String>(numberOfPairsOfCards: emojis?.count ?? defaultEmojis.count) {pairIndex in
            return (emojis?[pairIndex] ?? defaultEmojis[pairIndex])
        }
    }
    
    // MARK: - Access to the Model
    
    var cards: Array<MemoryGame<String>.Card> {
        self.model.cards
    }
    
    // MARK: - Intent(s)
    
    func choose(card: MemoryGame<String>.Card) {
        self.model.choose(card: card)
    }
    
    func resetGame() {
        self.model = EmojiMemoryGame.createMemoryGame(emojis: self.emojisContent)
    }
}
