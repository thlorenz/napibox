# napibox

Experimenting with the new napi Node.js addon API

## Build Xcode Project

A lot of times it is useful to debug an addon with Xcode.

To create an Xcode project for a particular example run the following from its directory.

```sh
node-gyp configure --debug -- -f xcode
```

Now you should have a `./build/binding.xcodeproj` which you can open. Configure the executable of the project in Xcode
as `node` and debug away :)

## Resources

- [docs](https://nodejs.org/api/n-api.html)
- [napi C++ API](https://github.com/nodejs/node-addon-api)
- [addon-examples](https://github.com/nodejs/abi-stable-node-addon-examples) showing both the C and C++ API
- [napi tests in Node.js core](https://github.com/nodejs/node/tree/master/test/addons-napi)
- [bcrypt port to napi C++ API](https://medium.com/@nicknaso/how-i-ported-bcrypt-to-new-n-api-d0b8c9fe6136)

## License

MIT
