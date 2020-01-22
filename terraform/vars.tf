variable "awsConfs" {
  type = object({
    region = string
    profile = string
  })

  default = {
    region = "sa-east-1"
    profile = "fred-invillia"
  }
}
