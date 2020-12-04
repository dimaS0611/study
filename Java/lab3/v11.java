package lab3;

public class v11 {
    public static void main(String[] args) {
        Time time = new Time(11, 45);
        Date date = new Date(23, 9, 2020);
        Day day = new Day(time, date);

        Time anotherTime = new Time(23, 45);
        Date anotherDate = new Date(28, 9, 2021);
        Day anotherDay = new Day(anotherTime, anotherDate);

        day.print();
        System.out.print("\n***********************\n");
        anotherDay.print();

        System.out.print("\n************************\n");
        System.out.print("Day1 + Day2: ");
        day.add(anotherDay).print();

        System.out.print("\n************************\n");
        System.out.print("Day1 - Day2: ");
        day.subtract(anotherDay).print();

        System.out.print("\n************************\n");
        System.out.print("Day1 > Day2: " + day.compareUp(anotherDay));

        System.out.print("\n************************\n");
        System.out.print("Day1 < Day2: " + day.compareDown(anotherDay));

        System.out.print("\n************************\n");
        System.out.print("Day1 == Day2: " + day.equals(anotherDay));

    }
}
