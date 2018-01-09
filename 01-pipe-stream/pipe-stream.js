'use strict'

const bindings = require('bindings')
const binding = bindings('pipe_stream')

const { StreamWritable } = binding

const writable = new StreamWritable()
console.log(writable)

const chunk = Buffer.from('hello world')
writable.write(chunk)
