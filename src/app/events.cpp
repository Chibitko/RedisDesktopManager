#include "events.h"

void Events::registerLoggerForConnection(RedisClient::Connection& c) {
  auto self = sharedFromThis().toWeakRef();
  QObject::connect(
      &c, &RedisClient::Connection::log, [self](const QString& info) {
        if (!self) return;
        emit self.toStrongRef()->log(QString("Connection: %1").arg(info));
      });

  QObject::connect(
      &c, &RedisClient::Connection::error, [self](const QString& error) {
        if (!self) return;
        emit self.toStrongRef()->log(QString("Connection: %1").arg(error));
      });
}
