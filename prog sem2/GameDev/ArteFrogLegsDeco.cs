using System;
using System.Collections.Generic;
using System.Text;
using Game_zakl;

namespace GameDev
{
    public class ArteFrogLegsDeco : ArtefactBase
    {
        public override Condition changeCondition() { return Condition.Weakened; }
        public override bool change()
        {
            return true;
        }
    }
}
