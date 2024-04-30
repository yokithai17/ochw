# Лабораторная 1. Взаимодействие с ОС через программный интерфейс
## Вариант 14

Вы очень любите путешествовать и делать фотографии на
профессиональный фотоаппарат. Фотоаппарат нумерует фотографии в
формате IMG_XXXXXX.jpg, где XXXXXX – шестизначный порядковый
номер фотографии. После того, как фотоаппарат называет файл
IMG_999999.jpg, он начинает нумерацию с нулевого номера –
IMG_000000.jpg. Если какой-то номер занят, то фотоаппарат берет следующий
номер для формирования названия файла. Если свободных номеров нет, то
фотоаппарат выдает ошибку: «Память заполнена».
Однажды в поездке в самый неудачный момент ваш фотоаппарат выдал
вам сообщение «Память заполнена». В спешке вы заменили карту памяти, не
использовав функцию «безопасного извлечения». Вернувшись домой, вы
«скинули» снимки с путешествия в отдельную папку и обнаружили, что
флешка была отформатирована в FAT32 и при ее неосторожном извлечении
были испорчены длинные имена файлов. Все файлы остались с короткими
именами вида IMG_~123.JPG, которые не совпадают с порядком, в котором
фото реально были сделаны. Спасает положение только сортировка по дате и
времени. Однако при просмотре этих фотографий на телевизоре присутствует
только вариант просмотра в порядке названия файлов.