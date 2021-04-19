//
//  WeatherView.m
//  WeatherApp
//
//  Created by Dzmitry Semenovich on 9.04.21.
//

#import "WeatherView.h"

@interface WeatherView ()
@end

@implementation WeatherView


- (void)viewDidLoad {
    [super viewDidLoad];
    
    if([self.passingString5 isEqualToString:@"Sunny"])
    {
        self.view.backgroundColor = [UIColor systemYellowColor];
    }
    if([self.passingString5 isEqualToString:@"Cloudy"] || [self.passingString5 isEqualToString:@"Mostly Clear"])
    {
        self.view.backgroundColor = [UIColor systemBlueColor];
    }
    if([self.passingString5 isEqualToString:@"Showers"])
    {
        self.view.backgroundColor = [UIColor systemGray2Color];
    }
    if([self.passingString5 isEqualToString:@"Foggy"])
    {
        self.view.backgroundColor = [UIColor systemGray4Color];
    }
    
    if([self.passingString1 isEqualToString:@"Minsk"])
    {
        self.libraryImage.image = [UIImage imageNamed:@"minsk"];
    }
    if([self.passingString1 isEqualToString:@"Brest"])
    {
        self.libraryImage.image = [UIImage imageNamed:@"brest"];
    }
    if([self.passingString1 isEqualToString:@"Beijing"])
    {
        self.libraryImage.image = [UIImage imageNamed:@"beijing"];
    }
    if([self.passingString1 isEqualToString:@"London"])
    {
        self.libraryImage.image = [UIImage imageNamed:@"london"];
    }
    if([self.passingString1 isEqualToString:@"Prague"])
    {
        self.libraryImage.image = [UIImage imageNamed:@"prague"];
    }
    if([self.passingString1 isEqualToString:@"New York"])
    {
        self.view.backgroundColor = [UIColor systemGray4Color];
        self.libraryImage.image = [UIImage imageNamed:@"newYork"];
    }
    
    
    self.cityName.text = self.passingString1;
    self.temperature.text = self.passingString2;
    self.humidity.text = self.passingString3;
    self.wind.text = self.passingString4;
    self.weather.text = self.passingString5;
    self.library.text = self.passingString6;
    
}

@end
