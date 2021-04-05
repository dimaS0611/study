using System;
using System.Threading.Tasks;
using System.Threading;
using GameDev;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Runtime.InteropServices;

namespace Game_zakl
{
    enum Gender
    {
        Male,
        Female
    }

    enum Race
    {
        Human,
        Gnome,
        Elf,
        Orc,
        Goblin
    }

    public enum Condition
    {
        Normal,
        Weakened,
        Ill,
        Poisoned,
        Paralyzed,
        Dead,
        Notchange
    }

    class PersonRP : IComparable<PersonRP>
    {

        static int ID = 1;
        private Gender gender_of_person;
        private int personal_ID;
        private Race race_of_person;
        private Condition condition_of_person;
        private string name_of_person;
        private uint age_of_person;
        private float current_amount_of_hp;
        private uint current_exp;
        private float max_hp;
        private bool status_res = false;//броня
        protected List<ArtefactInterface> m_inventory;

        public bool STATUS_RES
        {
            get
            {
                return status_res;
            }
            set
            {
                status_res = value;
            }
        }
        public int PERSONAL_ID
        {
            get
            {
                return personal_ID;
            }
            private set
            {
                personal_ID = value;
            }
        }
        public Gender GENDER_OF_PERSON
        {
            get
            {
                return gender_of_person;
            }
            private set
            {
                gender_of_person = value;
            }
        }
        public Race RACE_OF_PERSON
        {
            private set
            {
                race_of_person = value;
            }
            get
            {
                return race_of_person;
            }
        }
        public Condition CONDITION_OF_PERSON
        {
            get
            {
                return condition_of_person;
            }
            set
            {
                if (value == Condition.Dead)
                {
                    current_amount_of_hp = 0;
                }
                else
                {
                    condition_of_person = value;
                }
            }
        }
        public string NAME_OF_PERSON
        {
            get
            {
                return name_of_person;
            }
            private set
            {
                name_of_person = value;
            }
        }
        public uint AGE_OF_PERSON
        {
            get
            {
                return age_of_person;
            }
            set
            {
                age_of_person = value;
            }
        }
        public float CURRENT_AMOUNT_OF_HP
        {
            set
            {
                if (value < 0)
                {
                    throw new Exception("Текущее состояние здоровья не может быть меньше нуля!");
                }
                else if (value > max_hp)
                {
                    throw new Exception("Текущее состояние здоровье не может больше максимального");
                }
                else
                {
                    current_amount_of_hp = value;
                }

                if (value == 0)
                {
                    this.condition_of_person = Condition.Dead;
                }
                else if ((value / max_hp * 100) < 10)
                {
                    this.condition_of_person = Condition.Weakened;
                }
                else if ((value / max_hp * 100) >= 10)
                {
                    this.condition_of_person = Condition.Normal;
                }
            }
            get
            {
                return current_amount_of_hp;
            }
        }
        public uint CURRENT_EXP
        {
            set
            {
                current_exp = value;
            }
            get
            {
                return current_exp;
            }
        }
        public float MAX_HP
        {
            set
            {
                if (value <= 0)
                {
                    throw new Exception("Максимальное здоровье не может быть меньше или равняться нулю!");
                }
                else
                {
                    if (value < current_amount_of_hp)
                    {
                        current_amount_of_hp = value;
                    }
                    max_hp = value;
                }
            }
            get
            {
                return max_hp;
            }
        }
        public PersonRP(Gender value_gop, Race value_rof, Condition value_cop, String value_nop, uint value_aop, uint value_mh, uint value_caoh, uint value_ce)
        {
            m_inventory = new List<ArtefactInterface>();
            MAX_HP = value_mh;
            CURRENT_AMOUNT_OF_HP = value_caoh;
            GENDER_OF_PERSON = value_gop;
            RACE_OF_PERSON = value_rof;
            CONDITION_OF_PERSON = value_cop;
            NAME_OF_PERSON = value_nop;
            AGE_OF_PERSON = value_aop;
            CURRENT_EXP = value_ce;
            PERSONAL_ID = ID;

            ID++;
        }

        ~PersonRP() { }

        public string InfoCharacter()
        {
            string name = ("Имя персонажа: " + " " + (this.name_of_person).ToString() + " ");
            string id = ("ID:" + " " + (this.personal_ID).ToString() + " ");
            string gender = ("Пол:" + " " + (this.gender_of_person).ToString() + " ");
            string rasa = ("Раса:" + " " + (this.race_of_person).ToString() + " ");
            string condition = ("Состояние:" + " " + (this.condition_of_person).ToString() + " ");
            string age = ("Возраст:" + " " + (this.age_of_person).ToString() + " ");
            string maxhp = ("Максимальное здоровье:" + " " + (this.max_hp).ToString() + " ");
            string curhp = ("Текущее здоровье:" + " " + (this.current_amount_of_hp).ToString() + " ");
            string curexp = ("Текущий опыт:" + " " + (this.current_exp).ToString() + " ");

            return (name + id + gender + rasa + condition + age + maxhp + curhp + curexp);
        }

        public int CompareTo(PersonRP value)
        {
            return this.current_exp.CompareTo(value.current_exp);
        }
        public float hp_percents()
        {
            return current_amount_of_hp / max_hp * 100;
        }
        public void PickUpArtefact(ArtefactInterface item)
        {
            m_inventory.Add(item);
        }
        public void ApplyArtefact(int index, int power, PersonRP value)
        {
            if (value == null)
            {
                throw new Exception("Объект не передан.");
            }
            if (this.CONDITION_OF_PERSON != Condition.Dead && value.CONDITION_OF_PERSON != Condition.Dead)
            {
                var arte = m_inventory[index];

                arte.setPower(power);

                Condition temp = CONDITION_OF_PERSON;

                value.CURRENT_AMOUNT_OF_HP += arte.changeHP();
                if (arte.change())
                {
                    value.CONDITION_OF_PERSON = arte.changeCondition();
                }
                if (arte.changeCondition() == Condition.Notchange)
                    CONDITION_OF_PERSON = temp;

                if (!arte.renewable())
                {
                    m_inventory.Remove(arte);
                }
            }
            else
            {
                throw new Exception("Персонаж мёртв.");
            }
        }
        public void SetArtefactPower(int index, int power)
        {
            var arte = m_inventory[index];
            arte.setPower(power);
        }
        public void ThrowArtefact(int index)
        {
            m_inventory.RemoveAt(index);
        }
        public void PassArte(int index, PersonRP personTo)
        {
            var arte = this.m_inventory[index];
            personTo.m_inventory.Add(arte);

            this.m_inventory.Remove(arte);
        }
    }

    class MagicPersonRP : PersonRP
    {
        private bool speech;
        private bool move;
        private float max_magic;
        public float current_amount_of_magic;
        private int max_spell_number;
        private List<Spell> ListOfSpell;

        public bool SPEECH
        {
            get
            {
                return speech;
            }
            set
            {
                speech = value;
            }
        }
        public bool MOVE
        {
            get
            {
                return move;
            }
            set
            {
                move = value;
            }
        }
        public float CURRENT_AMOUNT_OF_MAGIC
        {
            get
            {
                return current_amount_of_magic;
            }
            set
            {
                if (value < 0)
                {
                    throw new Exception("Текущее состояние маны не может быть меньше нуля!");
                }
                else if (value > max_magic)
                {
                    throw new Exception("Текущее состояние маны не может больше максимального");
                }
                current_amount_of_magic = value;
                
            }
        }
        public float MAX_MAGIC
        {
            get
            {
                return max_magic;
            }
            set
            {
                if (value <= 0)
                {
                    throw new Exception("Максимальная запас маны не может быть меньше или равняться нулю!");
                }
                else
                {
                    if (value < current_amount_of_magic)
                    {
                        current_amount_of_magic = value;
                    }
                    max_magic = value;
                }
            }
        }
        public int MAX_SPELL_NUMBER
        {
            set
            {
                if (value < 0)
                {
                    throw new Exception("Максимальное число заклинаний в памяти чародея должно быть неотрицательным!");
                }
                else
                {
                    max_spell_number = value;
                }
            }
            get
            {
                return max_spell_number;
            }

        }

        public MagicPersonRP(Gender value_gop, Race value_rof, Condition value_cop, String value_nop, uint value_aop, uint value_caoh, uint value_ce, uint value_mh, uint value_caom, uint value_mm, bool value_speech, bool value_move, int Max_Spell_Number)
            : base(value_gop, value_rof, value_cop, value_nop, value_aop, value_caoh, value_ce, value_mh)
        {
            MAX_MAGIC = value_mm;
            CURRENT_AMOUNT_OF_MAGIC = value_caom;
            SPEECH = value_speech;
            MOVE = value_move;
            MAX_SPELL_NUMBER = Max_Spell_Number;
            ListOfSpell = new List<Spell>();
        }

        public void ApplyArtefact(int index, int power, MagicPersonRP value)
        {
            if (value == null)
            {
                throw new Exception("Объект не передан.");
            }
            if (this.CONDITION_OF_PERSON != Condition.Dead)
            {
                var arte = m_inventory[index];

                arte.setPower(power);

                Condition temp = CONDITION_OF_PERSON;

                value.CURRENT_AMOUNT_OF_MAGIC += arte.changeEXP();
                value.CURRENT_AMOUNT_OF_HP += arte.changeHP();
                value.CONDITION_OF_PERSON = arte.changeCondition();

                if (arte.changeCondition() == Condition.Notchange)
                    CONDITION_OF_PERSON = temp;

                if (!arte.renewable())
                {
                    m_inventory.Remove(arte);
                }
            }
            else
            {
                throw new Exception("Персонаж мёртв.");
            }
        }

        public bool AddSpell(Spell spell)
        {
            if (spell == null)
                throw new ArgumentNullException();
            if (ListOfSpell.Count == MAX_SPELL_NUMBER || ListOfSpell.IndexOf(spell) != -1)
                return false;
            ListOfSpell.Add(spell);
            return true;

        }
        public bool DeleteSpell(int a)
        {
            if (a < 0)
                return false;
            if (a >= ListOfSpell.Count)
                return false;
            ListOfSpell.RemoveAt(a);
            return true;
        }
        public bool DeleteSpell(Spell spell)
        {
            if (spell == null)
                throw new ArgumentNullException();
            int b = ListOfSpell.IndexOf(spell);
            return DeleteSpell(b);

        }
        public bool SpellDO(Spell spell, PersonRP receiver, int power)
        {
            int index = ListOfSpell.IndexOf(spell);
            if (index == -1)
                return false;
            return ListOfSpell[index].SpellDo(this, receiver, power);
        }
        public bool SpellDO(Spell spell, PersonRP receiver)
        {
            return SpellDO(spell, receiver, 0);
        }
        public bool SpellDO(Spell spell)
        {
            return SpellDO(spell, this, 0);
        }
        public bool SpellDO(Spell spell, int power)
        {
            return SpellDO(spell, this, power);
        }
    }

    interface DoSpell
    {
        bool SpellDo(MagicPersonRP sender, PersonRP receiver, int power);
    }

    abstract class Spell
    {
        private Thread th;
        protected float min_manacost;
        protected bool verb;
        protected bool move;
        protected int cd;
        static private bool Status_cd = false;
        protected float cost_on_value;
        // Свойства
        public float MIN_MANACOST
        {
            get
            {
                return min_manacost;
            }
        }
        public bool STATUS_CD
        {
            get
            {
                return Status_cd;
            }
        }
        public bool MOVE
        {
            get
            {
                return move;
            }
        }
        public bool Verb
        {
            get
            {
                return verb;
            }
        }
        public int CD
        {
            set
            {
                if (value <= 0)
                    throw new Exception("CD не должен быть меньше нуля!");
                cd = value;
            }
            get
            {
                return cd;
            }
        }
        public float COST_ON_VALUE
        {
            set
            {
                if (value < 0)
                    throw new Exception("Wrong format input: Cost per one mana value must not be less then 0!");
                cost_on_value = value;
            }
            get
            {
                return cost_on_value;
            }
        }
        public Spell(float mana, bool verb_component, bool Move, int Time, float Cost_on_value_)
        {
            if (mana < 0)
                throw new Exception("Wrong format input: Mana must not be less then 0!");
            if (Time <= 0)
                throw new Exception("Wrong format input: Time must not be less or equals 0!");
            COST_ON_VALUE = Cost_on_value_;
            min_manacost = mana;
            CD = Time;
            move = Move;
        }

        public Spell(bool verb_component, bool MOVE, int Time, float Cost_on_value_) : this(0, verb_component, MOVE, Time, Cost_on_value_)
        { } // не очень нужен

        private void CD_Do(int time)
        {
            th = new Thread(() =>
            {
                Status_cd = true;
                Thread.Sleep(time);
                Status_cd = false;
                th.Join();
            });
            th.Start();


        }
        protected abstract bool makeMagic(MagicPersonRP sender, PersonRP receiver, int power);

        public bool SpellDo(MagicPersonRP sender, PersonRP receiver, int power)
        {

            if (power < 0)
                throw new Exception("Мощность заклинания не может быть меньше 0");
            if (sender == null || receiver == null)
                throw new NullReferenceException("Должен быть указан человек на которого накладывается заклинание");
            if (Status_cd)
                return false;
            if (receiver.STATUS_RES)
                return false;
            if (sender.CONDITION_OF_PERSON == Condition.Dead || sender.CONDITION_OF_PERSON == Condition.Paralyzed)
                return false;
            if (verb && !sender.SPEECH)
                return false;
            if (move && !sender.MOVE)
                return false;
            float f = min_manacost + power * cost_on_value;
            if (sender.CURRENT_AMOUNT_OF_MAGIC < f)
            {
                //CD_Do(1000);
                return false;
            }
            if (makeMagic(sender, receiver, power))
            {
                sender.CURRENT_AMOUNT_OF_MAGIC -= f;
                CD_Do(cd);
                return true;
            }
            else
                return false;

        }

        //public sealed override string ToString() { return ""; }
    }

    class Healt_up : Spell
    {

        private float power_start = 2f;
        public Healt_up(bool verb_component, bool MOVE, int Time, float Cost_on_value_) : base(verb_component, MOVE, Time, Cost_on_value_)
        { }
        public Healt_up(float mana, bool verb_component, bool MOVE, int Time, float Cost_on_value_) : base(mana, verb_component, MOVE, Time, Cost_on_value_)
        { }
        public Healt_up(bool verb_component, int Time, float Cost_on_value_) : base(verb_component, false, Time, Cost_on_value_)
        { }
        protected override bool makeMagic(MagicPersonRP sender, PersonRP receiver, int power)
        {
            if (receiver.CONDITION_OF_PERSON == Condition.Dead)
                return false;// может быть отравлен стоит убрать(от этого зависит будет ли каст способности)

            float Power = power_start + power;// можно домножить на что-нибудь
            float new_hp = receiver.CURRENT_AMOUNT_OF_HP + Power;
            if (receiver.MAX_HP < new_hp)
                receiver.CURRENT_AMOUNT_OF_HP = receiver.MAX_HP;
            else
                receiver.CURRENT_AMOUNT_OF_HP = new_hp;
            return true;
        }
    }

    class ToCure : Spell
    {
        const float cost = 20;
        public ToCure(bool verb_component, bool MOVE, int Time) : base(cost, verb_component, MOVE, Time, 0)// - если есть ограничения на ману
        { }
        //public ToCure(float mana, bool verb_component,bool MOVE, int Time) : base(mana, verb_component, MOVE, Time, 0) - не нужно если есть ограничение на манакост
        //{ }
        public ToCure(bool verb_component, int Time) : base(cost, verb_component, false, Time, 0)
        { }
        protected override bool makeMagic(MagicPersonRP sender, PersonRP receiver, int power)
        {
            if (receiver.CONDITION_OF_PERSON != Condition.Ill)
                return false;//каст       
            if (receiver.hp_percents() >= 10f)
                receiver.CONDITION_OF_PERSON = Condition.Normal;
            else
                receiver.CONDITION_OF_PERSON = Condition.Weakened;
            return true;
        }

    }
    class Antidote : Spell
    {
        const float cost = 30;
        public Antidote(bool verb_component, bool MOVE, int Time) : base(cost, verb_component, MOVE, Time, 0)// - если  ограничения на ману
        { }
        //public Antidote(float mana, bool verb_component, bool MOVE, int Time) : base(mana, verb_component,MOVE, Time, 0) -не нужно если
        //{ }
        public Antidote(bool verb_component, int Time) : base(cost, verb_component, false, Time, 0)
        { }
        protected override bool makeMagic(MagicPersonRP sender, PersonRP receiver, int power)
        {
            if (receiver.CONDITION_OF_PERSON != Condition.Poisoned)
                return false;//каст        
            if (receiver.hp_percents() >= 10f)
                receiver.CONDITION_OF_PERSON = Condition.Normal;
            else
                receiver.CONDITION_OF_PERSON = Condition.Weakened;
            return true;
        }
    }

    class ToAlive : Spell
    {
        const float cost = 150;
        public ToAlive(bool verb_component, bool MOVE, int Time) : base(cost, verb_component, MOVE, Time, 0)// - если  ограничения на ману
        { }
        //public ToAlive(float mana, bool verb_component, bool MOVE, int Time) : base(mana, verb_component, bool MOVE, Time, 0) -не нужно если есть оговорка на ману
        //{ }
        public ToAlive(bool verb_component, int Time) : base(cost, verb_component, false, Time, 0)
        { }
        //public bool DoSpell(MagicPersonRP sender, PersonRP receiver)
        //{
        //    return SpellDo(sender, receiver);
        //}
        protected override bool makeMagic(MagicPersonRP sender, PersonRP receiver, int power)
        {
            if (receiver.CONDITION_OF_PERSON != Condition.Dead)
                return false;
            receiver.CURRENT_AMOUNT_OF_HP = 1;

            return true;
        }

    }

    class Armor : Spell
    {
            const float cost = 50;
            public Armor(bool verb_component, bool MOVE, int Time, int power) : base(cost, verb_component, MOVE, Time, power)// - если  ограничения на ману
            { }
            //public Armor(float mana, bool verb_component, bool MOVE, int Time, int power) : base(mana, verb_component, MOVE, Time, power) -не нужно если есть оговорка на ману
            //{ }
            public Armor(bool verb_component, int Time, int power) : base(cost, verb_component, false, Time, power)
            { }
            protected override bool makeMagic(MagicPersonRP sender, PersonRP receiver, int power)
            {
                if (receiver.CONDITION_OF_PERSON == Condition.Dead)
                    return false;
                receiver.STATUS_RES = true;
                Thread a = new Thread(() =>
                {
                    Thread.Sleep(power + 1000);
                    receiver.STATUS_RES = false;
                });
                a.Start();
                return true;
            }

    }

    class UnFreeze : Spell
    {
            const float cost = 85;
            public UnFreeze(bool verb_component, bool MOVE, int Time) : base(cost, verb_component, MOVE, Time, 0)// - если  ограничения на ману
            { }
            //public UnFreeze(float mana, bool verb_component, bool MOVE, int Time) : base(mana, verb_component, MOVE, Time, 0) -не нужно если есть оговорка на ману
            //{ }
            public UnFreeze(bool verb_component, int Time) : base(cost, verb_component, false, Time, 0)
            { }
            //public bool DoSpell(MagicPersonRP sender, PersonRP receiver)
            //{
            //    return SpellDo(sender, receiver);
            //}
            protected override bool makeMagic(MagicPersonRP sender, PersonRP receiver, int power)
            {
                if (receiver.CONDITION_OF_PERSON != Condition.Paralyzed)
                    return false;//каст        
                receiver.CURRENT_AMOUNT_OF_HP = 1;
                return true;
            }

    }
        
} 
