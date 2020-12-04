using System;
using System.Collections.Generic;
using System.Text;
using Game_zakl;

namespace GameDev
{
    public enum ArteLivingWaterVolume
    {
        small = 10,
        medium = 25,
        large = 50
    }

    //живая вода
    public class ArteLivingWater : ArtefactBase
    {
        ArteLivingWaterVolume m_volume;
        public ArteLivingWater(ArteLivingWaterVolume volume)
        {
            m_volume = volume;
        }

        int GetVolume()
        {
            return (int)m_volume;
        }

        public override int changeHP()
        {
            return GetVolume();
        }
        
        

    }
}
