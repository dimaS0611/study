using System;
using System.ComponentModel.Design;
using Game_zakl;
using GameDev;

namespace Game
{
    class Program
    {
        static void Main(string[] args)
        {
            PersonRP Andrew = new PersonRP(Gender.Male, Race.Human,Condition.Normal,"Andrew", 18, 100, 20, 100);
            PersonRP Tommy = new PersonRP(Gender.Male, Race.Human, Condition.Normal, "Andrew", 18, 100, 5, 50);
            Console.WriteLine("Информация о персонаже: " + Andrew.InfoCharacter());
            Console.WriteLine("Сравнение по опыту: " + Andrew.CompareTo(Tommy));
            Console.WriteLine("HP в процентах: " + Tommy.hp_percents());
            ArteDeadWater adw = new ArteDeadWater(ArteDeadWaterVolume.large);
            ArteDeadWater adw_2 = new ArteDeadWater(ArteDeadWaterVolume.large);
            ArteDeadWater adw_3 = new ArteDeadWater(ArteDeadWaterVolume.large);
            ArteFrogLegsDeco afld = new ArteFrogLegsDeco();
            MagicPersonRP Kim = new MagicPersonRP(Gender.Male, Race.Human, Condition.Normal, "Kim", 18, 100, 90, 50, 2000, 5000, true, true, 30);
            MagicPersonRP Jenek = new MagicPersonRP(Gender.Male, Race.Human, Condition.Poisoned, "Jenek", 18, 100, 90, 50, 2000, 5000, true, true, 30);
            MagicPersonRP Dima = new MagicPersonRP(Gender.Male, Race.Human, Condition.Dead,"Dima", 18, 100, 90, 50, 2000, 5000, true, true, 30);
            Console.WriteLine("Состояние маны изначально: " + Kim.CURRENT_AMOUNT_OF_MAGIC);
            Kim.PickUpArtefact(adw);
            Kim.PickUpArtefact(adw_3);
            Kim.ApplyArtefact(0,0, Kim);
            Console.WriteLine("Состояние маны после мёртвой воды: " + Kim.CURRENT_AMOUNT_OF_MAGIC);
            Kim.SetArtefactPower(0, 100);
            Kim.PickUpArtefact(adw_2);
            Kim.ThrowArtefact(1);
            //Kim.PassArte(0,Tommy);
            Tommy.PickUpArtefact(afld);
            Console.WriteLine("Состояние до: " + Tommy.CONDITION_OF_PERSON);
            Tommy.ApplyArtefact(0, 0, Tommy);
            Console.WriteLine("Состояние после: " + Tommy.CONDITION_OF_PERSON);
            ArteLightninhStaff als = new ArteLightninhStaff();
            Tommy.PickUpArtefact(als);
            Console.WriteLine("ХП до посоха: " + Kim.CURRENT_AMOUNT_OF_HP);
            Tommy.ApplyArtefact(0, 10, Kim);
            Console.WriteLine("ХП после посоха: " + Kim.CURRENT_AMOUNT_OF_HP);
            ArteLivingWater alw = new ArteLivingWater(ArteLivingWaterVolume.large);
            Tommy.PickUpArtefact(alw);
            Console.WriteLine("ХП до воды: " + Tommy.CURRENT_AMOUNT_OF_HP);
            Tommy.ApplyArtefact(1, 0, Tommy);
            Console.WriteLine("ХП после воды: " + Tommy.CURRENT_AMOUNT_OF_HP);
            ArteVasiliskEye ave = new ArteVasiliskEye();
            Tommy.PickUpArtefact(ave);
            Console.WriteLine("Состояние до Василиска: " + Tommy.CONDITION_OF_PERSON);
            Tommy.ApplyArtefact(1, 0, Tommy);
            Console.WriteLine("Состояние после Василиска: " + Tommy.CONDITION_OF_PERSON);
            ArtePoisonousSaliva aps = new ArtePoisonousSaliva();
            Tommy.PickUpArtefact(aps);
            Console.WriteLine("Состояние до слюны: " + Kim.CONDITION_OF_PERSON + " " + Kim.CURRENT_AMOUNT_OF_HP);
            Tommy.ApplyArtefact(1, 0, Kim);
            Console.WriteLine("Состояние после слюны: " + Kim.CONDITION_OF_PERSON + " " + Kim.CURRENT_AMOUNT_OF_HP);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            Healt_up hu = new Healt_up(true, true, 20, 5);
            Kim.AddSpell(hu);
            Console.WriteLine("Здоровье до заклинания: " + Kim.CURRENT_AMOUNT_OF_HP);
            Kim.SpellDO(hu);
            Console.WriteLine("Здоровье после заклинания: " + Kim.CURRENT_AMOUNT_OF_HP);
            Kim.CONDITION_OF_PERSON = Condition.Ill;
            ToCure tc = new ToCure(true, 20);
            Kim.AddSpell(tc);
            Console.WriteLine("Состояние до заклинания: " + Kim.CONDITION_OF_PERSON);
            Kim.SpellDO(tc);
            Console.WriteLine("Состояние после заклинания: " + Kim.CONDITION_OF_PERSON);
            Kim.CONDITION_OF_PERSON = Condition.Poisoned;
            Antidote antd = new Antidote(true, 20);
            Jenek.AddSpell(antd);
            Jenek.SpellDO(antd);
            Console.WriteLine("Состояние после заклинания: " + Jenek.CONDITION_OF_PERSON);
            ToAlive ta = new ToAlive(true, 20);
            Dima.AddSpell(ta);
            Dima.SpellDO(ta,Dima);
            Console.WriteLine("Состояние после заклинания: " + Dima.CONDITION_OF_PERSON);
            Armor arm = new Armor(true, 20, 50000);
            Jenek.AddSpell(arm);
            Jenek.SpellDO(arm);
            Console.WriteLine("Броня после заклинания: " + Jenek.STATUS_RES);
            UnFreeze ufr = new UnFreeze(true, 20);
            Kim.CONDITION_OF_PERSON = Condition.Paralyzed;
            Jenek.AddSpell(ufr);
            Jenek.SpellDO(ufr,Kim);
            Console.WriteLine("После анфриз: " + Kim.CONDITION_OF_PERSON + " " + Kim.CURRENT_AMOUNT_OF_HP);


        }
    }
}
