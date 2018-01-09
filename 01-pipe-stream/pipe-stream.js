'use strict'

const fs = require('fs')
const Writable = require('./writable')

const writable = new Writable()

// Piping small chunks for illustration purposes
fs
  .createReadStream(__filename, { highWaterMark: 32 })
  .pipe(writable)
