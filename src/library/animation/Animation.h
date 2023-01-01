//
// Created by noartem on 01.01.2023.
//

#ifndef ELEMENTOR_ANIMATION_H
#define ELEMENTOR_ANIMATION_H

#include "../Element.h"

#include <chrono>
#include <ctime>

namespace elementor {
    enum class AnimationState {
        Pending,
        Executing,
        Stoped,
    };

    template<typename Duration = std::chrono::milliseconds>
    class Animation {
    public:
        Animation(ApplicationContext *ctx, int duration, std::function<void (float value)> callback) {
            this->ctx = ctx;
            this->duration = duration;
            this->callback = callback;
        }

        void start() {
            if (this->state != AnimationState::Pending) {
                return;
            }

            this->state = AnimationState::Executing;
            this->startedAt = this->now();

            ctx->requestNextFrame([this] { this->iter(); });
        }


        void stop() {
            this->state = AnimationState::Stoped;
        }

    private:
        AnimationState state = AnimationState::Pending;
        ApplicationContext *ctx;
        int duration;
        int startedAt = -1;
        float lastValue = -1;
        std::function<void (float value)> callback;

        int now() {
            return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

        void iter() {
            if (this->state != AnimationState::Executing) {
                return;
            }

            int now = this->now();

            float value = ((float) (now - this->startedAt)) / ((float) this->duration);
            float valueNormalized = std::min(std::max(value, ZERO), ONE);

            if (this->lastValue != valueNormalized) {
                callback(valueNormalized);
            } else {
                this->lastValue = valueNormalized;
            }

            if (value < ONE) {
                ctx->requestNextFrame([this] {
                    this->iter();
                });
            }
        }
    };

    template<typename Duration = std::chrono::milliseconds>
    Animation<Duration> *animation(ApplicationContext *ctx, int duration, std::function<void (float value)> callback) {
        return new Animation<Duration>(ctx, duration, callback);
    }
}

#endif //ELEMENTOR_ANIMATION_H