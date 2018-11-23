#include "controller.h"

QT_BEGIN_NAMESPACE

Controller::Controller() : QObject() {
}

Controller::Controller(QObject *parent) : QObject(parent)
  , m_target(nullptr)
  , m_matrix()
  , m_angle(0.0f){
    this->axis = QVector3D(0.0f, 1.0f, 0.0f);
    this->point = QVector3D(0.0f, 0.0f, 0.0f);
}

void Controller::setTarget(Qt3DCore::QTransform *target){
    if (m_target != target){
        m_target = target;
        emit targetChanged();
    }
}

Qt3DCore::QTransform *Controller::target() const {
    return m_target;
}

void Controller::setAngle(float angle){
    if (!qFuzzyCompare(angle, m_angle)){
        m_angle = angle;
        updateMatrix();
        emit angleChanged();
    }
}

void Controller::setAngle(int n, float angle){
    this->previousAngle[n] = this->angle();
    if (!qFuzzyCompare(angle, m_angle)){
        m_angle = angle;
        updateMatrix();
        emit angleChanged();
    }
}

float Controller::angle() const {
    return m_angle;
}

float Controller::angle(int n){
    return this->previousAngle[n];
}

void Controller::updateMatrix(){
    QVector3D aux = QVector3D(this->point.x(), this->point.y(), this->point.z());
    m_target->setMatrix(this->target()->rotateAround(aux, this->m_angle, this->axis));
}

void Controller::setAxis(QVector3D naxis){
    this->axis = naxis;
}

void Controller::setAxis(int n, QVector3D naxis){
    this->previousAxis[n] = this->axis;
    this->axis = naxis;
}

void Controller::setPoint(QVector3D npoint){
    this->point = npoint;
}

void Controller::setPoint(int n, QVector3D npoint){
    this->previousPoint[n] = this->point;
    this->point = npoint;
}

QVector3D Controller::getAxis(){
    return this->axis;
}

QVector3D Controller::getAxis(int n){
    return this->previousAxis[n];
}

QVector3D Controller::getPoint(){
    return this->point;
}

QVector3D Controller::getPoint(int n){
    return this->previousPoint[n];
}

void Controller::setPreviousAxis(QVector3D axis[3]){
    this->previousAxis[0] = axis[0];
    this->previousAxis[1] = axis[1];
    this->previousAxis[2] = axis[2];
}

void Controller::setPreviousPoint(QVector3D point[3]){
    this->previousPoint[0] = point[0];
    this->previousPoint[1] = point[1];
    this->previousPoint[2] = point[2];
}

void Controller::setPreviousAngle0(float angle){
    this->previousAngle[0] = angle;
}

void Controller::setPreviousAngle1(float angle){
    this->previousAngle[1] = angle;
}

void Controller::setPreviousAngle2(float angle){
    this->previousAngle[2] = angle;
}

QT_END_NAMESPACE
