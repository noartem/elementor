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
        Playing,
        Paused,
        Finished,
    };

    template<typename Duration = std::chrono::milliseconds>
    class Animation {
    public:
        Animation(const std::shared_ptr<ApplicationContext> &ctx, int duration,
                  const std::function<float(float value)> &timing, const std::function<void(float value)> &callback) {
            this->ctx = ctx;
            this->timing = timing;
            this->duration = duration;
            this->callback = callback;
        }

        void play() {
            if (this->state != AnimationState::Pending) {
                return;
            }

            this->state = AnimationState::Playing;
            this->startedAt = this->now();

            ctx->requestNextFrame([this] { this->iter(); });
        }

        void pause() {
            this->state = AnimationState::Paused;
        }

        void finish() {
            this->state = AnimationState::Finished;

            if (this->lastValue < ONE) {
                this->callback(ONE);
            }
        }

        void reverse() {
            this->lastValue = ONE - this->lastValue;
            this->reversed = !this->reversed;
        }

    private:
        AnimationState state = AnimationState::Pending;
        std::shared_ptr<ApplicationContext> ctx;
        int duration{};
        int startedAt = -1;
        float lastValue = -1;
        bool reversed = false;
        std::function<void(float value)> callback;
        std::function<float(float value)> timing;

        int now() {
            return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

        void iter() {
            if (this->state != AnimationState::Playing) {
                return;
            }

            int now = this->now();

            float value = ((float) (now - this->startedAt)) / ((float) this->duration);
            value = std::min(std::max(value, ZERO), ONE);
            if (this->reversed) value = ONE - value;
            if (this->timing) value = this->timing(value);

            if (this->lastValue != value) {
                this->callback(value);
            } else {
                this->lastValue = value;
            }

            if (value < ONE) {
                this->ctx->requestNextFrame([this] {
                    this->iter();
                });
            }
        }
    };

    template<typename Duration = std::chrono::milliseconds>
    std::shared_ptr<Animation<Duration>>
    animation(std::shared_ptr<ApplicationContext> ctx, int duration, std::function<void(float value)> callback) {
        return new Animation<Duration>(ctx, duration, nullptr, callback);
    }

    template<typename Duration = std::chrono::milliseconds>
    std::shared_ptr<Animation<Duration>>
    animation(std::shared_ptr<ApplicationContext> ctx, int duration, std::function<float(float value)> timing,
              std::function<void(float value)> callback) {
        return new Animation<Duration>(ctx, duration, timing, callback);
    }
}

#endif //ELEMENTOR_ANIMATION_H