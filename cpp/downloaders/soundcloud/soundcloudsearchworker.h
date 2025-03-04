// soundcloudsearchworker.h
#ifndef SOUNDCLOUDSEARCHWORKER_H
#define SOUNDCLOUDSEARCHWORKER_H

#include "soundcloud.h"
#include <QObject>
#include <QDebug>
#include <pybind11/pybind11.h>

class SoundcloudSearchWorker : public QObject
{
    Q_OBJECT
public:
    explicit SoundcloudSearchWorker(const std::string& repo_path, const QString& query, QObject* parent = nullptr)
        : QObject(parent), m_repo_path(repo_path), m_query(query) {

    }

signals:
    void searchCompleted(const std::vector<SoundcloudItem>& results);

public slots:
    void performSearch() {
        //py::scoped_interpreter guard{};
        py::gil_scoped_acquire gil;
        try {
            SoundcloudWrapper wrapper(m_repo_path);
            auto results = wrapper.search(m_query.toStdString(), 20);
            qDebug() << "finished search";
            emit searchCompleted(results);
        } catch (const std::exception &ex) {
            qDebug() << "Error in performSearch: " << ex.what();
        }
    }

private:
    std::string m_repo_path;
    QString m_query;
};

#endif // SOUNDCLOUDSEARCHWORKER_H
