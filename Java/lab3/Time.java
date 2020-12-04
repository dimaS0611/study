package lab3;

public class Time {
    int m_hour;
    int m_min;

    public Time()
    {}

    public Time(int hour, int min)
    {
        if(hour < 0)
            System.exit(1);

        if(hour >= 24) {
            Date date = new Date();
            date.m_day +=  (hour /24) - 1;
            hour += (hour % 24) - 24;
        }


        if(min < 0)
            System.exit(1);

        if(min >= 60) {
            hour += min / 60;
            min %= 60;
        }

        this.m_hour = hour;
        this.m_min = min;
    }

    public Time(Time anotherTime)
    {
        this.m_hour = anotherTime.m_hour;
        this.m_min = anotherTime.m_min;
    }

    public Time add(Time time)
    {
        int hour = 0, min = 0;

        hour = this.m_hour + time.m_hour;
        min = this.m_min + time.m_min;

        Time sumTime = new Time(hour, min);

        return sumTime;
    }

    public Time subtract(Time time)
    {
        int hour = 0, min = 0;

        if(this.CompareUp(time))
            hour = this.m_hour - time.m_hour;
            min = this.m_min - time.m_min;

        if(this.CompareDown(time))
            hour = time.m_hour - this.m_hour;
            min = time.m_min - this.m_min;

        if(hour < 0)
            hour = 0;
        if(min < 0)
            min = 0;

        Time subtractTime = new Time(Math.abs(hour), Math.abs(min));

        return  subtractTime;
    }

    public boolean CompareUp(Time time)
    {
        if(this.m_hour > time.m_hour)
            return true;

        if(this.m_hour == time.m_hour && this.m_min > time.m_min)
            return true;

        return false;
    }

    public boolean CompareDown(Time time)
    {
        if(this.m_hour < time.m_hour)
            return true;

        if(this.m_hour == time.m_hour && this.m_min < time.m_min)
            return true;

        return false;
    }

    public  boolean Equals(Time time)
    {
        if(this.m_hour == time.m_hour && this.m_min == time.m_min)
            return true;

        return false;
    }

    public  void print()
    {
        System.out.print(this.m_hour + " : " + this.m_min);
    }







}
