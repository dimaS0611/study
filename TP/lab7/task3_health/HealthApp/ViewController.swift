//
//  ViewController.swift
//  HealthApp
//
//  Created by Dzmitry Semenovich on 12.04.21.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet weak var ageLabel: UITextField!
    
    @IBOutlet weak var heightLabel: UITextField!
    
    @IBOutlet weak var weightLabel: UITextField!
    
    @IBOutlet weak var sexSegmentControl: UISegmentedControl!
    
    @IBOutlet weak var traningsNumSegmentControl: UISegmentedControl!
    
    @IBOutlet weak var resultLabel: UILabel!
    
    override func viewDidLoad() {
     
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }

    @IBAction func Calculate(_ sender: Any)
    {
        var bmr : Double = 0.0
        var amr : Double = 0.0
        
        let age = Double(ageLabel.text ?? "") ?? 0
        let height = Double(heightLabel.text ?? "") ?? 0
        let weight = Double(weightLabel.text ?? "") ?? 0
        
        
        if sexSegmentControl.selectedSegmentIndex == 0
        {
            bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age)
        }
        else
        {
            bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age)
        }
        
        if traningsNumSegmentControl.selectedSegmentIndex == 0
        {
            amr = 1.2
        }
        if traningsNumSegmentControl.selectedSegmentIndex == 1
        {
            amr = 1.375
        }
        if traningsNumSegmentControl.selectedSegmentIndex == 2
        {
            amr = 1.55
        }
        if traningsNumSegmentControl.selectedSegmentIndex == 3
        {
            amr = 1.725
        }
        if traningsNumSegmentControl.selectedSegmentIndex == 4
        {
            amr = 1.9
        }
        
        let calories = Int(bmr * amr)
        let bmi = Int(weight / (pow(height / 100, 2)))
        
        resultLabel.text = "You should eat : \(calories) calories to keep your weight. Your body mass index : \(bmi)"
    }
    
}

