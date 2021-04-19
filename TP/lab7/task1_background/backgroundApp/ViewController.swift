//
//  ViewController.swift
//  backgroundApp
//
//  Created by Dzmitry Semenovich on 9.04.21.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var labelIndicator: UILabel!
    @IBOutlet weak var switchIndicator: UISwitch!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        labelIndicator.text = "Background image: bg1.jpg"
        labelIndicator.textColor = UIColor.white
        
        view.backgroundColor = UIColor(patternImage: UIImage(named: "bg1")!)
    }

    @IBAction func switchTapped(_ sender: Any) {
        if switchIndicator.isOn
        {
            labelIndicator.text = "Background image: bg1.jpg"
            view.backgroundColor = UIColor(patternImage: UIImage(named: "bg1")!)
        }
        else{
            labelIndicator.text = "Background image: bg2.jpg"
            view.backgroundColor = UIColor(patternImage: UIImage(named: "bg2")!)
        }
    }
    
}

