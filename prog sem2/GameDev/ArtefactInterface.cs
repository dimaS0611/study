using System;
using System.Collections.Generic;
using System.Text;
using Game_zakl;

namespace GameDev
{
    public interface ArtefactInterface
    {
        int power(); // мощность артефакта
        void setPower(int power);
        int changeHP();
        uint changeEXP();
        bool change();


        bool renewable(); // признак возобновляемости

        Condition changeCondition();
    }

    
    public class ArtefactBase : ArtefactInterface
    {
        public virtual int power() { return 0; }

        public virtual bool renewable() { return false; }

        public virtual Condition changeCondition() { return Condition.Notchange; }
        public virtual bool change() { return false; }
        public virtual int changeHP() { return 0; }

        public virtual uint changeEXP() { return 0; }
        public virtual void setPower(int power) { }

    }
}
