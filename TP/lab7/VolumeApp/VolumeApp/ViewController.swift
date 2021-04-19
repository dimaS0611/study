//
//  ViewController.swift
//  VolumeApp
//
//  Created by Dzmitry Semenovich on 14.04.21.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var radiusLabel: UITextField!
    
    @IBOutlet weak var heightLabel: UITextField!
    
    @IBOutlet weak var objectSegmentControl: UISegmentedControl!
    
    @IBOutlet weak var resultLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }

    @IBAction func calculate(_ sender: Any)
    {
        let radius = Double(radiusLabel.text!) ?? 0.0
        let height = Double(heightLabel.text!) ?? 0.0
        
        let result = volume(radius, height)
        
        resultLabel.text = "The volume of \(objectSegmentControl.titleForSegment(at: objectSegmentControl.selectedSegmentIndex) ?? "-") = \(result.rounded(FloatingPointRoundingRule.toNearestOrAwayFromZero))"
    }
    
    /// Function that calculate volume of column or cylinder
    ///
    /// - Parameter radius : Radius of the object
    /// - Parameter height : Height of the object
    /// - Returns : Volume of the object
    func volume(_ radius: Double, _ height: Double) -> Double
    {
        var volume : Double = 0.0
        let s = Double.pi * pow(radius, 2.0)
        
        if objectSegmentControl.selectedSegmentIndex == 0 {
            volume = (height / 3) * s
        }
        else {
            volume = height * s
        }
        
        return volume
    }
}

