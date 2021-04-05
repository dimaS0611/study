import Foundation

let numOfDay = 279

let numOfweek : Int = numOfDay / 7
let day : Int = numOfDay - numOfweek * 7

switch day
{
case 1:
    print("Monday")
case 2:
    print("Tuesday")
case 3:
    print("Wedensday")
case 4:
    print("Thursday")
case 5:
    print("Friday")
case 6:
    print("Saturday")
case 7:
    print("Sunday")
default:
    print("None")
}



