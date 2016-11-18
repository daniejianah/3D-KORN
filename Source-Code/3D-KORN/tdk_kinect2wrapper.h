#ifndef TDK_KINECT2WRAPPER_H
#define TDK_KINECT2WRAPPER_H

#include <QObject>
#include <QDebug>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include "kinect2_grabber.h"

class TDK_Kinect2Wrapper : public QObject
{
    Q_OBJECT
public:
    explicit TDK_Kinect2Wrapper(QObject *parent = 0);
    void startKinect();
    boost::mutex mutex;

    boost::shared_ptr<pcl::Grabber> mv_grabber;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr mv_cloud;
    boost::function<void( const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& )> mv_pointCloudCallback =
            [this]( const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& ptr ){

        qDebug("Callback fn : Inside callback fn");
        boost::mutex::scoped_lock lock(mutex);
        qDebug("Callback fn : Acquired lock");
        setMv_cloud(ptr);
        qDebug("Callback fn : Point cloud set -> "+ptr->size());

    };

    pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr getMv_cloud() const;
    void setMv_cloud(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &value);

signals:
    void signalCloudUpdated(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& ptr);

public slots:

};

#endif // TDK_KINECT2WRAPPER_H