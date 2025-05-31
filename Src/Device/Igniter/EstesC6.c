#include "../../../Inc/Device/Igniter/EstesC6.h"

void EstesC6_init(Igniter* instance) {
  instance->ignite = (Igniter_ignite)EstesC6_ignite;
  instance->tick = (Igniter_ignite)EstesC6_tick;
  instance->errorStatus.value = 0;
  instance->status.value = 0;
}

void EstesC6_ignite(Igniter* instance, uint32_t timestamp_ms) {
  instance->gpio->write(instance->gpio, GPIO_VALUE_HIGH);
  instance->igniteTimestamp_ms = timestamp_ms;
}

void EstesC6_tick(Igniter* instance, uint32_t timestamp_ms) {
  if (timestamp_ms - instance->igniteTimestamp_ms >= instance->igniteDuration_ms) {
    instance->gpio->write(instance->gpio, GPIO_VALUE_LOW);
  }
}