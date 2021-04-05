using System;
using System.Collections.Generic;
using System.Text;
using Game_zakl;

namespace GameDev
{
    public class ArteVasiliskEye : ArtefactBase
    {
        public override Condition changeCondition() { return Condition.Paralyzed; }
        public override bool change()
        {
            return true;
        }
    }
}
