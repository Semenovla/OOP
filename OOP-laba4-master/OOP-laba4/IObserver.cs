using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_laba4
{
    public interface IObserver
    {//ble, чтобы уведомить своих наблюдателей о том, что свойство объекта изменилось. 
     //Он принимает объект типа IObservable в качестве первого аргумента, свойство объекта
     //в качестве второго аргумента и массив аргументов в качестве третьего аргумента.
     //Если второй и/или третий аргумент не переданы, то они имеют значение null.
        void OnPropertyChanged(IObservable subject, string property = null, object[] args = null);
        List<IObservable> GetSubjects();//Этот метод возвращает список объектов, реализующих интерфейс IObservable, за которыми наблюдает данный наблюдатель.
    }
}
