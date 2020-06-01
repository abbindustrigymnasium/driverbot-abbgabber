<template>
  <v-container>
    <v-slider v-model="onoff" min="0" max="1" label="Off / On"> </v-slider>
    <v-slider v-model="velocity" min="0" max="200" label="Hastighet"></v-slider>
    <v-slider v-model="direction" min="0" max="180" label="Riktning"></v-slider>
    <v-col cols="120" sm="60">
      <p>Velocity = {{ this.velocity - 100 }}</p>
      <p>Direction = {{ this.direction - 90 }}</p>
    </v-col>
  </v-container>
</template>

<script>
const mqtt = require("mqtt");
export default {
  name: "HelloWorld",

  data: () => ({
    client: "",
    velocity: "100",
    direction: "90",
    onoff: "0",
  }),

  //Connects to mqtt
  created() {
    this.client = mqtt.connect("ws://maqiatto.com:8883/ws", {
      username: "gabriel.bergdahl@abbindustrigymnasium.se",
      password: "qazwsxedc",
    });
  },
  mounted() {
    setInterval(() => {
      this.sendPayload();
    }, 1000);
  },
  methods: {
    // Sends the payload every 1/10 second
    sendPayload() {
      if (this.onoff !== 0) {
        // Uses the velocity from the slider as value and repeats 0s to make it easier to substring
        let fast =
          "0".repeat(4 - this.velocity.toString().length) +
          this.velocity.toString();
        // Uses the angle from the slider as value and repeats 0s to make it easier to substring
        let angles =
          "0".repeat(4 - this.direction.toString().length) +
          this.direction.toString();
        // Publishes the full message with both values
        this.client.publish(
          "gabriel.bergdahl@abbindustrigymnasium.se/driverbot",
          fast.toString() + angles.toString()
        );
      } else {
        // When pressing off resets the values to standard, 0 speed and angle.
        this.client.publish(
          "gabriel.bergdahl@abbindustrigymnasium.se/driverbot",
          "01000090"
        );
      }
    },
  },
};
</script>
