using System;
using System.Collections.Generic;
using System.Text;
using Game_zakl;

namespace GameDev
{
    public class ArteLightninhStaff : ArtefactBase
    {
        int m_maxPower = 40;
        int m_power;

        
        public override bool renewable() { return true; }

        public override int changeHP()
        {
            return -m_power;
        }

        public override void setPower(int power)
        {
            m_power = Math.Min(power, m_maxPower);
        }

    }
}
