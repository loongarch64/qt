#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <QSGItem>
#include <QDebug>
#include "particlesystem.h"

class ParticleEmitter : public QSGItem
{
    Q_OBJECT
    //###currently goes in emitters OR sets system. Pick one?
    Q_PROPERTY(ParticleSystem* system READ system WRITE setSystem NOTIFY systemChanged)
    Q_PROPERTY(ParticleType* particle READ particle WRITE setParticle NOTIFY particleChanged)
    Q_PROPERTY(bool emitting READ emitting WRITE setEmitting NOTIFY emittingChanged)

    Q_PROPERTY(int particlesPerSecond READ particlesPerSecond WRITE setParticlesPerSecond NOTIFY particlesPerSecondChanged)
    Q_PROPERTY(int particleDuration READ particleDuration WRITE setParticleDuration NOTIFY particleDurationChanged)

public:
    explicit ParticleEmitter(QSGItem *parent = 0);
    virtual void emitWindow(int timeStamp);

    ParticleType* particle() {return m_particle;}

    bool emitting() const
    {
        return m_emitting;
    }

    int particlesPerSecond() const
    {
        return m_particlesPerSecond;
    }

    int particleDuration() const
    {
        return m_particleDuration;
    }

    ParticleSystem* system() const
    {
        return m_system;
    }

signals:
    void particlesPerSecondChanged(int);
    void particleDurationChanged(int);
    void emittingChanged(bool);

    void particleChanged(ParticleType* arg);
    void systemChanged(ParticleSystem* arg);

public slots:

    void setEmitting(bool arg);

    void setParticlesPerSecond(int arg)
    {
        if (m_particlesPerSecond != arg) {
            m_particlesPerSecond = arg;
            emit particlesPerSecondChanged(arg);
        }
    }

    void setParticleDuration(int arg)
    {
        if (m_particleDuration != arg) {
            m_particleDuration = arg;
            emit particleDurationChanged(arg);
        }
    }

    void setParticle(ParticleType* arg)
    {
        if (m_particle != arg) {
            m_particle = arg;
            emit particleChanged(arg);
        }
    }

    void setSystem(ParticleSystem* arg)
    {
        if (m_system != arg) {
            m_system = arg;
            m_system->registerParticleEmitter(this);
            emit systemChanged(arg);
        }
    }

protected:
    ParticleType* m_particle;
    ParticleSystem* m_system;
    int m_particlesPerSecond;
    int m_particleDuration;
    bool m_emitting;
};

#endif // PARTICLEEMITTER_H