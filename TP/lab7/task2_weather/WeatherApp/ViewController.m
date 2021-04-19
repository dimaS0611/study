//
//  ViewController.m
//  WeatherApp
//
//  Created by Dzmitry Semenovich on 9.04.21.
//

#import "ViewController.h"
#import "WeatherView.h"

@interface ViewController ()
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor colorWithPatternImage: [UIImage imageNamed:@"startScreen.jpg"]];

    temperatureData = [NSMutableDictionary dictionary];
    windData = [NSMutableDictionary dictionary];
    weatherData = [NSMutableDictionary dictionary];
    humidityData = [NSMutableDictionary dictionary];
    libraryData = [NSMutableDictionary dictionary];
    
    [temperatureData setValue: [NSNumber numberWithInt: 10] forKey:@"Minsk"];
    [temperatureData setValue: [NSNumber numberWithInt: 14] forKey:@"London"];
    [temperatureData setValue: [NSNumber numberWithInt: 13] forKey:@"Brest"];
    [temperatureData setValue: [NSNumber numberWithInt: 15] forKey:@"New York"];
    [temperatureData setValue: [NSNumber numberWithInt: 10] forKey:@"Prague"];
    [temperatureData setValue: [NSNumber numberWithInt: 11] forKey:@"Beijing"];
    
    [windData setValue: [NSNumber numberWithInt: 23] forKey:@"Minsk"];
    [windData setValue: [NSNumber numberWithInt: 4] forKey:@"London"];
    [windData setValue: [NSNumber numberWithInt: 7] forKey:@"Brest"];
    [windData setValue: [NSNumber numberWithInt: 10] forKey:@"New York"];
    [windData setValue: [NSNumber numberWithInt: 20] forKey:@"Prague"];
    [windData setValue: [NSNumber numberWithInt: 15] forKey:@"Beijing"];
    
    [weatherData setValue: @"Sunny" forKey:@"Minsk"];
    [weatherData setValue: @"Foggy" forKey:@"London"];
    [weatherData setValue: @"Showers" forKey:@"Brest"];
    [weatherData setValue: @"Showers" forKey:@"New York"];
    [weatherData setValue: @"Cloudy" forKey:@"Prague"];
    [weatherData setValue: @"Mostly Clear" forKey:@"Beijing"];
    
    [humidityData setValue: [NSNumber numberWithInt: 23] forKey:@"Minsk"];
    [humidityData setValue: [NSNumber numberWithInt: 40] forKey:@"London"];
    [humidityData setValue: [NSNumber numberWithInt: 15] forKey:@"Brest"];
    [humidityData setValue: [NSNumber numberWithInt: 60] forKey:@"New York"];
    [humidityData setValue: [NSNumber numberWithInt: 20] forKey:@"Prague"];
    [humidityData setValue: [NSNumber numberWithInt: 15] forKey:@"Beijing"];
    
    [libraryData setValue: @"National Library" forKey:@"Minsk"];
    [libraryData setValue: @"British Library" forKey:@"London"];
    [libraryData setValue: @"Tech Univericty Library" forKey:@"Brest"];
    [libraryData setValue: @"New York Public Library" forKey:@"New York"];
    [libraryData setValue: @"National Czech Library" forKey:@"Prague"];
    [libraryData setValue: @"National Library of China" forKey:@"Beijing"];
    
    self.textField.delegate = self;
}

- (IBAction)refresh:(id)sender
{
    WeatherView *wv = [self.storyboard instantiateViewControllerWithIdentifier:@"weatherView"];
    
    NSString *city = self.textField.text;
    NSNumber *temperature = temperatureData[city];
    NSNumber *humidity = humidityData[city];
    NSString *weather = weatherData[city];
    NSNumber *wind = windData[city];
    NSString *library = libraryData[city];
    
    wv.passingString1 = city;
    wv.passingString2 = temperature.stringValue;
    wv.passingString3 = humidity.stringValue;
    wv.passingString4 = wind.stringValue;
    wv.passingString5 = weather;
    wv.passingString6 = library;
    
    [self presentViewController:wv animated:YES completion:nil];
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    return [textField resignFirstResponder];
}

@end
