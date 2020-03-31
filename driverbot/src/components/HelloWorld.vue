<template>
  <v-container>
    <v-btn @click="sendPayload()">
      Click me!
    </v-btn>
  </v-container>
</template>

<script>
const mqtt = require("mqtt");
export default {
  name: "HelloWorld",

  data: () => ({
    client: "",
    payload: "YEs"
  }),

  mounted: function() {
    this.client = mqtt.connect("ws://maqiatto.com:8883/ws", {
      username: "gabriel.bergdahl@abbindustrigymnasium.se",
      password: "qazwsxedc"
    });
  },
  methods: {
    sendPayload() {
      this.client.publish(
        "gabriel.bergdahl@abbindustrigymnasium.se/driverbot",
        this.payload
      );
      console.log(this.payload);
    }
  }
};
</script>
