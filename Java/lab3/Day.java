package lab3;

public class Day {
    Time m_time = new Time();
    Date m_date = new Date();

    public Day()
    {}

    public Day(Time time, Date date)
    {
        this.m_time = time;
        this.m_date = date;
    }

    public Date getDate()
    {
        return m_date;
    }

    public Time getTime()
    {
        return m_time;
    }

    public Day add(Day day)
    {
        Time time = new Time();
        time = day.getTime();

        Date date = new Date();
        date = day.getDate();

        Time resTime = new Time();
        resTime = this.m_time.add(time);
        Date resDate = new Date();
        resDate = this.m_date.add(date);

        Day res = new Day(resTime, resDate);

        return res;
    }

    public Day subtract(Day day)
    {
        Time time = new Time();
        time = day.getTime();

        Date date = new Date();
        date = day.getDate();

        Time resTime = new Time();
        resTime = this.m_time.subtract(time);
        Date resDate = new Date();
        resDate = this.m_date.subtract(date);

        Day res = new Day(resTime, resDate);

        return res;
    }

    public boolean compareUp(Day day)
    {
        Time time = new Time();
        time = day.getTime();

        Date date = new Date();
        date = day.getDate();
        if(this.m_date.CompareUp(date))
            return true;

        if(this.m_date.Equal(date) && this.m_time.CompareUp(time))
            return true;

        return  false;
    }

    public boolean compareDown(Day day)
    {
        Time time = new Time();
        time = day.getTime();

        Date date = new Date();
        date = day.getDate();

        if(this.m_date.CompareDown(date))
            return true;

        if(this.m_date.Equal(date) && this.m_time.CompareDown(time))
            return true;

        return  false;
    }

    public boolean equals(Day day)
    {
        Time time = new Time();
        time = day.getTime();

        Date date = new Date();
        date = day.getDate();

        if(this.m_time.equals(time) && this.m_date.equals(date))
            return true;

        return false;
    }

    public void print()
    {
        System.out.print("Date: ");
        m_date.print();
        System.out.print("\nTime: ");
        m_time.print();
    }
}
