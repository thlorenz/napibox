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

## License

MIT
