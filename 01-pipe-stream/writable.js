'use strict'

const bindings = require('bindings')
const binding = bindings('pipe_stream')
const { StreamWritable } = binding

const stream = require('stream')
const Writable = stream.Writable

class WritableWrapper extends Writable {
  constructor(opts = {}) {
    super(opts)
    this._writable = new StreamWritable()
  }

  _write(chunk, encoding, cb) {
    this._writable.write(chunk)
    cb()
  }
}

module.exports = WritableWrapper
