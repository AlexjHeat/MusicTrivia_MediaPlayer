#include "playlist.h"

void swap(Song* a, Song* b)
{
    Song temp = *a;
    *a = *b;
    *b = temp;
}

int partition (Song arr[], int low, int high)
{
    Song pivot = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
        return (i + 1);
}

void quickSort(Song arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

Playlist::Playlist()
{
    n = 0;
    changed = false;
}

Playlist::Playlist(QString name)
{
    this->name = name;
    n = 0;
    changed = true;
}


QString Playlist::getName() { return name; }
void Playlist::setName(QString name) { this->name = name; changed = true;}
bool Playlist::getChanged(){ return changed; }
void Playlist::setChanged(bool changed){ this->changed = changed; }

void Playlist::add(QString fileName)
{
    if(!fileName.isEmpty()) {
        list[n].setPath(fileName);
        n++;
    }
}

void Playlist::remove(int j)
{
    n--;
    for (int i = j; i < n; i++)
    {
        list[i] = list[i+1];
    }
}

void Playlist::sort()
{
    int low = 0;
    int high = n - 1;
    quickSort(list, low, high);
}

void Playlist::save()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr,"Save Playlist", "", "Playlist (*.plt)");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Failed to save");
        return;
    }

    QTextStream out(&file);
    out << n << Qt::endl << name << Qt::endl;
    for(int i = 0; i < n; i++)
    {
        out << list[i];
    }
    file.flush();
    file.close();
    changed = false;
}

void Playlist::load(QFile &file)
{
    QTextStream in(&file);

    in >> n;
    in.readLine();
    name = in.readLine();

    for(int i = 0; i < n; i++)
    {
        in >> list[i];
        in.readLine();
    }
}

QStringList Playlist::getList()
{
    QStringList result;
    for(int i = 0; i < n; i++)
    {
        if(!list[i].getArtist().isEmpty())
        {
            if(!list[i].getTitle().isEmpty())
                result << list[i].getArtist() + " - " + list[i].getTitle();
            else
                result << list[i].getArtist();
        }
        else
        {
            result << list[i].getPath();
        }
    }
    return result;
}

Song& Playlist::getSong(int i)
{
    return list[i];
}
