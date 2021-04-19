//
//  ViewController.h
//  WeatherApp
//
//  Created by Dzmitry Semenovich on 9.04.21.
//

#import <UIKit/UIKit.h>

NSDictionary *temperatureData;
NSDictionary *windData;
NSDictionary *weatherData;
NSDictionary *humidityData;
NSDictionary *libraryData;

@interface ViewController : UIViewController<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *textField;

@end

