## Лаб. 3 Начальное знакомство с API ОС
# Задание
Необходимо разработать приложение, которое при помощи чистого WinAPI будет создавать окно, обрабатывать клики
мыши и нажатия клавиш, а также сохранять свое состояние и восстанавливать его при последующем запуске.
1) По умолчанию окно размером 320 на 240 px должно быть закрашено синим цветом с красной сеткой линий NxN.
2) Размер поля (переменная N) по умолчанию выбирается на усмотрение программиста. Однако, пользователь
имеет возможность переопределить размер поля, указав его в качестве аргумента командной строки при запуске
приложения.
3) Окно существует и обрабатывает события до тех пор, пока пользователь не закрыл его. При закрытии окна
происходит завершение приложения.
4) При клике левой клавишей мыши на поле должен быть нарисован круг определенного цвета в той ячейке поля, в
которую произошел клик.
5) При клике правой клавишей мыши на поле должен быть нарисован крестик определенного цвета в той ячейке поля,
в которую произошел клик. Цвет элементов поля (крестиков и кружков) выбирается на усмотрение программиста.
6) Если пользователь нажал на клавиатуре Ctrl+Q или ESC, окно должно закрыться.
7) Если пользователь нажал на клавиатуре Shift+C, должен запуститься блокнот.
8) Если пользователь нажал ENTER, фоновый цвет поля должен измениться на случайный.
9) При прокрутке пользователем колеса мыши текущий цвет линий сетки должен плавно изменяться.
    
Смену цвета фона необходимо организовать при помощи подмены кисти окна. Использование сообщения WM_PAINT
для данной подзадачи не предполагается.


Предпочтительно реализовывать приложение на C/C++, однако допустимо использование любого языка программирования по согласованию с преподавателем и при условии соблюдения следующих двух пунктов:
1. Использование чистого WinAPI без всяких оберток (FFI, типа питоньего ctypes, не в счет).
2. Ручное управление ресурсами в рамках задания лабораторной, то есть не забывать делать DeleteObject и т.п.
"Здесь это делать не нужно, среда сама сделает" - не катит. Все, что в задание не входит (отладочный вывод,
дополнительные навороты), можно пользовать как угодно, лишь бы программа работала корректно.
Приложение должно использовать функции WinAPI там, где это возможно. Если эквивалентные функции есть в
стандартной библиотеке выбранного языка программирования и в WinAPI, необходимо использовать функцию WinAPI.

### Критерии оценивания лабораторной работы

Само собой предполагается, что студент безупречно разбирается в коде программы и может ответить на вопросы по
деталям реализации и особенностям работы приложения.

3) Программа реагирует на события мыши и меняет цвет линий в соответствии с заданием - 5 баллов
4) Программа реагирует на события клавиатуры и выполняет действия в соответствии с заданием - 4 балла
5) Окно программы адекватно реагирует на операции сворачивания, изменения размера и т.п., производя перерисовку
без лагов - 4 балла
6) Программа обрабатывает параметр командной строки - 2 балла
7)  Программа корректно использует и утилизирует ресурсы (все ресурсы)- 3 балла
8)  Программа работает стабильно, не падает и не зависает - 2 балла