@Library('conservify') _

conservifyProperties()

timestamps {
    node () {
        conservifyBuild(name: 'sonar', archive: "build/firmware/module/*.bin, build/firmware/test/*.bin")
        distributeFirmware(directory: "build/firmware/module")
    }

    refreshDistribution()
}
