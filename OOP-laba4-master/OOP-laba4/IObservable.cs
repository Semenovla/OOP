using System.Collections.Generic;

namespace OOP_laba4
{
    public interface IObservable
    {
        //Этот метод принимает объект типа IObserver в качестве аргумента и добавляет его в список наблюдателей.
        void AddObserver(IObserver observer);
        //Этот метод принимает объект типа IObserver в качестве аргумента и удаляет его из списка наблюдателей.
        void RemoveObserver(IObserver observer);
       // Этот метод удаляет всех наблюдателей из списка.
        void RemoveAllObserver();
        //Этот метод возвращает список всех наблюдателей, которые в данный момент наблюдают за этим объектом.
        List<IObserver> GetObservers();
        //Этот метод принимает объект типа IObserver в качестве аргумента и возвращает true, если этот объект в данный момент наблюдает за этим объектом.
        bool isObserver(IObserver observer);
        void NotifyAll(string property = null, object[] args = null);//Этот метод уведомляет всех наблюдателей о изменении состояния этого объекта. Он принимает два необязательных аргумента - свойство, которое изменилось, и массив аргументов, связанных с изменением свойства.
    }
}
