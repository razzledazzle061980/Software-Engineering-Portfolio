import { NgModule, inject } from '@angular/core';
import {CanActivateFn, RouterModule, Routes, RouterStateSnapshot, Router, ActivatedRouteSnapshot} from '@angular/router';
import { TripListingComponent} from "./trip-listing/trip-listing.component";
import { AddTripComponent} from "./add-trip/add-trip.component";
import { EditTripComponent} from "./edit-trip/edit-trip.component";
import { AuthenticationService} from "./services/authentication.service";
import {LoginComponent} from "./login/login.component";

const authGuard: CanActivateFn = (next: ActivatedRouteSnapshot, state: RouterStateSnapshot) => {
  const authService: AuthenticationService = inject(AuthenticationService);
  const router: Router = inject(Router);

  if (!authService.tokenSubject.getValue()) {
    router.navigate(['/login']);
    return false;
  }
  return true;
};

const logoutGuard: CanActivateFn = (next: ActivatedRouteSnapshot, state: RouterStateSnapshot) => {
  const authService: AuthenticationService = inject(AuthenticationService);
  authService.logout();
  return true;
}

const routes: Routes = [
  { path: '', component: TripListingComponent, pathMatch: 'full', canActivate: [authGuard] },
  { path: 'add-trip', component: AddTripComponent, canActivate: [authGuard] },
  { path: 'edit-trip/:tripCode', component: EditTripComponent, canActivate: [authGuard] },
  { path: 'logout', component: LoginComponent, canActivate: [logoutGuard] },
  { path: 'login', component: LoginComponent }

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
