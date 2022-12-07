# Arduino <> Firebase <> Android

## summary
| Category | Unit |
| ------------- | ------------- |
| MCU  | Wemos D1  |
| Sensor | PIR HC-SR04 |
| Output | LCD 20x4 I2C |
| Cloud | Firebase Realtime Database |

## installation
- create project on firebase
- configure your Realtime Database
- download `google-services.json` from your firebase project
- put `google-services.json` to `app/` directory
- edit `FIREBASE HOST` and `FIREBASE AUTH` in iot.ino
- build your APK

## demo
![](imgs/implementation.jpg)

## scheme
![](imgs/a.png)

## firebase realtime database
```json
{
  "Data": {
    "keluar": 13,
    "masuk": 18,
    "total": 5
  },
  "Suhu": [
    {
      "suhu": 35.05001
    },
    {
      "suhu": 34.96999
    }
  ]
}
```

## contributors
Muhammad Humam Zaky, Reza Daffa, Yoga Indra Wijaya