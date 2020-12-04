using System;
using System.Collections.Generic;
using System.Text;
using Game_zakl;

namespace GameDev
{
    public class ArtePoisonousSaliva : ArtefactBase
    {
        int m_power = -60;
        
        public override bool renewable() { return true; }
        public override int power() { return m_power; }
        public override int changeHP()
        {
            return m_power;
        }
        public override bool change()
        {
            return true;
        }
        public override Condition changeCondition() { return Condition.Poisoned; }

    }
}
