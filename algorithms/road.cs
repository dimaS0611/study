using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace roads
{
    public class DSU
    {
        ArrayList size = new ArrayList();
        ArrayList parent = new ArrayList();

        public void init(int n)
        {
            for(int i = 0; i < n; ++i)
            {
                size.Add(1);
                parent.Add(i);
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {

        }
    }
}
