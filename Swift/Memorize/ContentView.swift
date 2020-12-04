//
//  ContentView.swift
//  Memorize
//
//  Created by Dima Semenovich on 7/22/20.
//  Copyright © 2020 Dima Semenovich. All rights reserved.
//

import SwiftUI

//var content: Array<String> = EmojiStorage.getArrayOfTheme(key : EmojiStorage.emojis.helloween)

struct ContentView: View {
    @ObservedObject var viewModel: EmojiMemoryGame
    var body: some View {
        
        VStack{
            HStack{
            
                Button(action: {
                withAnimation(.easeOut) {
                    self.viewModel.resetGame()
                }
                }, label: { Text("New Game") })
            
            }
            Grid(viewModel.cards) { card in
               CardView(card: card).onTapGesture {
                    withAnimation(.linear(duration: 0.75)) {
                    self.viewModel.choose(card: card)
                }
            }
                .padding(5)

        }
                .foregroundColor(Color.orange)
                .padding()
                .font(Font.largeTitle)
                    }
    }
}



struct CardView : View {
    var card: MemoryGame<String>.Card
    
    var body: some View {
        GeometryReader { geometry in
            self.body(for: geometry.size)
        }
    }
    @State private var animatedBonusRemaining: Double = 0
    
    private func startBonusTimeAnimation() {
        animatedBonusRemaining = card.bonusRemaining
        withAnimation(.linear(duration: card.bonusTimeRemaining)) {
            animatedBonusRemaining = 0
        }
    }
    
    @ViewBuilder
    private func body(for size: CGSize) -> some View {
        if card.isFaceUp || !card.isMatched {
           ZStack {
            Group {
                if card.isConsumingBonusTime {
                    Pie(startAngle: Angle.degrees(0-90), endAngle: Angle.degrees(-animatedBonusRemaining*360-90), clockwise: true)
                        .onAppear {
                            self.startBonusTimeAnimation()
                        }
                } else {
                    Pie(startAngle: Angle.degrees(0-90), endAngle: Angle.degrees(-card.bonusRemaining*360-90), clockwise: true)
                }
            }.padding(5).opacity(0.45)
                .transition(.identity)
            
            Text(self.card.content)
                    .font(Font.system(size: fontSize(for: size)))
                    .rotationEffect(Angle.degrees(card.isMatched ? 360 : 0))
                    .animation(card.isMatched ?  Animation.linear(duration: 1).repeatForever(autoreverses: false) : .default)
           }
           .cardify(isFaceUp: card.isFaceUp)
           .transition(AnyTransition.scale )
        }
    }
    //MARK: - Drawing Constants

    private func fontSize(for size: CGSize) -> CGFloat {
        min(size.width, size.height) * 0.7
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        let gameContent = GameContent(content: <#[String]#>)
        
        let game = EmojiMemoryGame(emojisArray: gameContent)
        game.choose(card: game.cards[0])
        return ContentView(viewModel: game)
    }
}

