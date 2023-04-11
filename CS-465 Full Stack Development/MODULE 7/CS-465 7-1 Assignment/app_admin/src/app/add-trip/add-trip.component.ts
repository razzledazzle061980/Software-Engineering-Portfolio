import { Component } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from "@angular/forms";
import { TripsService } from "../services/trips.service";
import { Router } from "@angular/router";

@Component({
  selector: 'app-add-trip',
  templateUrl: './add-trip.component.html',
  styleUrls: ['./add-trip.component.css']
})
export class AddTripComponent {
  addForm: FormGroup;
  submitted = false;

  constructor(
    private formBuilder: FormBuilder,
    private tripsService: TripsService,
    private router: Router
  ) {
    this.addForm = this.formBuilder.group({
      _id: [],
      code: ['', Validators.required],
      name: ['', Validators.required],
      length: ['', Validators.required],
      start: ['', Validators.required],
      resort: ['', Validators.required],
      perPerson: ['', Validators.required],
      image: ['', Validators.required],
      description: ['', Validators.required],
    })
  }

  addTrip() {
    if (this.addForm.valid) {
      this.tripsService.addTrip(this.addForm.value)
        .subscribe( {
          next: () => this.router.navigate(['/']),
          error: err => console.log(err)
        });
    }
  }

  get f() { return this.addForm.controls; }
}
