//
//  WeatherView.h
//  WeatherApp
//
//  Created by Dzmitry Semenovich on 9.04.21.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


@interface WeatherView : UIViewController<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UILabel *cityName;

@property (weak, nonatomic) IBOutlet UILabel *temperature;

@property (weak, nonatomic) IBOutlet UILabel *weather;

@property (weak, nonatomic) IBOutlet UILabel *wind;

@property (weak, nonatomic) IBOutlet UILabel *humidity;

@property (weak, nonatomic) IBOutlet UILabel *library;

@property (weak, nonatomic) IBOutlet UIImageView *libraryImage;

@property (strong, nonatomic)NSString *passingString1;

@property (strong, nonatomic)NSString *passingString2;

@property (strong, nonatomic)NSString *passingString3;

@property (strong, nonatomic)NSString *passingString4;

@property (strong, nonatomic)NSString *passingString5;

@property (strong, nonatomic)NSString *passingString6;

@end

NS_ASSUME_NONNULL_END
