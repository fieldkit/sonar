@Library('conservify') _

conservifyProperties()

timestamps {
    node () {
        conservifyBuild(name: 'sonar')

        build job: "distribution", wait: false
    }
}
