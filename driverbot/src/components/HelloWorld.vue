<template>
  <v-container>
    <v-slider v-model="onoff" min="0" max="1" label="On / Off"> </v-slider>
    <v-slider
      v-model="velocity"
      min="-100"
      max="100"
      label="Hastighet"
    ></v-slider>
    <v-slider
      v-model="direction"
      min="-90"
      max="90"
      label="Riktning"
    ></v-slider>
  </v-container>
</template>

<script>
const mqtt = require("mqtt");
export default {
  name: "HelloWorld",

  data: () => ({
    client: "",
    payload: "YEs",
    velocity: "0",
    direction: "0",
    onoff: "1",
  }),

  created() {
    this.client = mqtt.connect("ws://maqiatto.com:8883/ws", {
      username: "gabriel.bergdahl@abbindustrigymnasium.se",
      password: "qazwsxedc",
    });
  },
  mounted() {
    setInterval(() => {
      this.sendPayload();
    }, 2000);
  },
  methods: {
    sendPayload() {
      if (this.onoff !== 0) {
        if (this.direction !== 0 || this.velocity !== 0) {
          this.client.publish(
            "gabriel.bergdahl@abbindustrigymnasium.se/driverbot",
            this.velocity.toString() + " " + this.direction.toString()
          );
        }
      }
    },
  },
};
</script>
