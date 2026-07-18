# WebAudio for Node.js

This is a part of [Node3D](https://github.com/node-3d) project.

[![NPM](https://badge.fury.io/js/@node-3d%2Fwebaudio.svg)](https://badge.fury.io/js/@node-3d/webaudio)
[![Lint](https://github.com/node-3d/webaudio/actions/workflows/lint.yml/badge.svg)](https://github.com/node-3d/webaudio/actions/workflows/lint.yml)
[![Test](https://github.com/node-3d/webaudio/actions/workflows/test.yml/badge.svg)](https://github.com/node-3d/webaudio/actions/workflows/test.yml)
[![Cpplint](https://github.com/node-3d/webaudio/actions/workflows/cpplint.yml/badge.svg)](https://github.com/node-3d/webaudio/actions/workflows/cpplint.yml)

```console
npm install @node-3d/webaudio
```

## Binary Provenance

Release binary archives for this package are published by public GitHub Actions
workflows.
When a release asset includes a GitHub Artifact Attestation, you can verify that
the downloaded archive was published by the visible workflow in this repository:

```console
gh release download <tag> -R node-3d/webaudio -p <platform>.gz
gh attestation verify <platform>.gz -R node-3d/webaudio
```

The attestation links the archive to the repository, workflow, commit, and
release build identity. It does not replace review of the source code, workflow,
or third-party library contents.

> This addon is ABI-compatible across Node.js versions. **There is no compilation** during `npm install`.


**Node.js** addon implementing the
[Web Audio Api](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API).

Import any class you like from the module and then follow the
[doc](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API):

```js
import { AudioContext } from '@node-3d/webaudio'; // usually this is enough
```

**This module is WORK IN PROGRESS.**
Some features are missing for good.

Currently exported classes:

* `AudioBuffer`
* `AudioContext`
* `AudioParam`
* `AnalyserNode`
* `BiquadFilterNode`
* `ConvolverNode`
* `GainNode`
* `PannerNode`
* `AudioBufferSourceNode`
* `OscillatorNode`
* `AudioScheduledSourceNode`

In examples directory, currently working examples are prepended with `_`.
