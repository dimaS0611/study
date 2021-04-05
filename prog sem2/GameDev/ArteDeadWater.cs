using System;
using System.Collections.Generic;
using System.Text;
using Game_zakl;

namespace GameDev
{
    public enum ArteDeadWaterVolume
    {
        small = 10,
        medium = 25,
        large = 50
    }


    //мертвая вода
    public class ArteDeadWater : ArtefactBase
    {
        ArteDeadWaterVolume m_volume;

        public ArteDeadWater(ArteDeadWaterVolume volume)
        {
            m_volume = volume;
        }

        uint GetVolume()
        {
            return (uint)m_volume;
        }

        public override uint changeEXP()
        {
            return GetVolume();
        }
    }
}
